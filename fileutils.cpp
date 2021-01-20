#include "gameitems/note.h"
#include "fileutils.h"

#include <QDebug>

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

static NoteType columnToType[] = {
    NoteType::NORMALDOWN,
    NoteType::BONUS,
    NoteType::TRAP,
    NoteType::NORMALUP,
    NoteType::BONUS,
    NoteType::TRAP,
    NoteType::SMASH
};

static void tokenizeOsuFile(QTextStream &, QMap<QString, QString> *, QList<QString> *);

void tokenizeOsuFile(QTextStream &instream, QMap<QString, QString> *info_tokens, QList<QString> *notes_tokens)
{
    /* Regexes for the different contents */
    QRegularExpression sectionrx("\\[([^]]+)\\]");
    QRegularExpression propertyrx("([^:\\d]+):\\s*(.+)");
    QRegularExpression hitobjectrx("(\\d+,\\d+,\\d+),.+");

    QString section = "Invalid";
    QString line;

    while (instream.readLineInto(&line))
    {
        QRegularExpressionMatch sectionmatch = sectionrx.match(line);
        QRegularExpressionMatch propertymatch = propertyrx.match(line);
        QRegularExpressionMatch hitobjectmatch = hitobjectrx.match(line);

        if (sectionmatch.hasMatch())
            section = sectionmatch.capturedTexts()[1];
        if (info_tokens && propertymatch.hasMatch())
            info_tokens->insert(section + "/" + propertymatch.capturedTexts()[1], propertymatch.capturedTexts()[2]);
        if (notes_tokens && hitobjectmatch.hasMatch())
            notes_tokens->append(hitobjectmatch.capturedTexts()[1]);
    }
}

bool loadHighscoreFile(QString &path, Rank *rank, QList<int> *scores)
{
    qDebug() << "loading highscores from file: '" + path + "'";

    /* Open the file */
    QFile infile(path);
    if (!infile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "error opening file: " + infile.errorString();
        return false;
    }

    QTextStream in(&infile);
    QString jsonstring = in.readAll();
    QJsonDocument jsondoc = QJsonDocument::fromJson(jsonstring.toUtf8());
    QJsonObject root = jsondoc.object();

    QJsonValue rankvalue = root["rank"];
    if (!rankvalue.isDouble()) { /* pas de type int en json, on est obligés de valider avec un double */
        qDebug() << "the file contains an invalid rank value and will be ignored: " << rankvalue;
        return false;
    }
    *rank = (Rank) rankvalue.toInt();

    QJsonValue scorevalue = root["scorelist"];
    if (!scorevalue.isArray()) {
        qDebug() << "the file does not contain a correct score list and will be ignored: " << scorevalue;
        return false;
    }

    QJsonArray scoresarray = root["scorelist"].toArray();
    for (QJsonValue val : scoresarray) {
        if (val.isDouble())
            scores->append(val.toInt());
        else
            qDebug() << "the file contains an invalid score value that is not an integer which will be ignored: " << val;
    }

    qDebug() << "highscore file loaded with rank value = " + QString::number(*rank) + " and " + QString::number(scores->size()) + " score entries";

    return true;
}

bool writeHighscoreFile(QString &path, Rank rank, QList<int> *scores)
{
    qDebug() << "writing highscores to file: '" + path + "'";

    /* Open the file */
    QFile outfile(path);
    if (!outfile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "error opening file: " + outfile.errorString();
        return false;
    }

    QJsonDocument jsondocument;
    QJsonObject root;

    root["rank"] = (int) rank;

    QJsonArray scorearray;
    for (int score : *scores) {
        scorearray.append(score);
    }

    root["scorelist"] = scorearray;

    jsondocument.setObject(root);

    qDebug() << "highscores succesfully saved";

    /* par défaut toJson écrit de l'UTF-8 et c'est aussi l'encodage qu'on utilise à la lecture (là explicitement par contre) */
    outfile.write(jsondocument.toJson());

    return true;
}

bool loadOsuFileMetadata(QString &path, QMap<QString, QString> *metadata)
{
    qDebug() << "loading metadata from file: '" + path + "'";

    /* Open the file */
    QFile infile(path);
    if (!infile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "error opening file: " + infile.errorString();
        return false;
    }

    QTextStream in(&infile);

    tokenizeOsuFile(in, metadata, nullptr);

    /* lire les metadonnées de la musique */

    QString title = (*metadata)["Metadata/Title"];
    QString artist = (*metadata)["Metadata/Artist"];
    QString relative_music_path = (*metadata)["General/AudioFilename"];

    qDebug() << QString::asprintf("artist: '%s', title: '%s'", title.toStdString().c_str(), artist.toStdString().c_str());
    qDebug() << QString::asprintf("relative audio file path: '%s'", relative_music_path.toStdString().c_str());

    return true;
}

bool loadOsuFile(QString &path, QList<Note *> *upNotes, QList<Note *> *downNotes)
{
    qDebug() << "loading file: '" + path + "'";

    /* Open the file */
    QFile infile(path);
    if (!infile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "error opening file: " + infile.errorString();
        return false;
    }

    QTextStream in(&infile);

    QMap<QString, QString> info_tokens;
    QList<QString> notes_tokens;
    tokenizeOsuFile(in, &info_tokens, &notes_tokens);

    /* lire les metadonnées de la musique */

    QString relative_music_path = info_tokens["General/AudioFilename"];
    qDebug() << QString::asprintf("relative audio file path: '%s'", relative_music_path.toStdString().c_str());

    /* lire les notes dans les listes */

    for (QString note : notes_tokens)
    {
        QStringList settings_list = note.split(',');
        int x = settings_list.takeFirst().toInt();
        int y = settings_list.takeFirst().toInt(); // not important
        int timestamp = settings_list.takeFirst().toInt();
        Q_UNUSED(y);

        int column = (x * 7) / 512;
        NoteType type = columnToType[column];

        if (column > 2)
        {
            Note *new_note = new Note(type, timestamp);
            upNotes->append(new_note);
        }
        else
        {
            Note *new_note = new Note(type, timestamp);
            downNotes->append(new_note);
        }
    }

    qDebug() << QString::asprintf("read %d notes (%d up, %d down)", notes_tokens.size(), upNotes->size(), downNotes->size());

    infile.close();
    return true;
}
