#include "GameItems/note.h"
#include "fileutils.h"

#include <QDebug>

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

static NoteType columnToType[] = {
    NoteType::NORMALDOWN,
    NoteType::BONUS,
    NoteType::TRAP,
    NoteType::NORMALUP,
    NoteType::BONUS,
    NoteType::TRAP,
    NoteType::SMASH
};

static void tokenize(QTextStream &, QMap<QString, QString> &, QList<QString> &);

void tokenize(QTextStream &instream, QMap<QString, QString> &info_tokens, QList<QString> &notes_tokens)
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
        if (propertymatch.hasMatch())
            info_tokens.insert(section + "/" + propertymatch.capturedTexts()[1], propertymatch.capturedTexts()[2]);
        if (hitobjectmatch.hasMatch())
            notes_tokens.append(hitobjectmatch.capturedTexts()[1]);
    }
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
    tokenize(in, info_tokens, notes_tokens);

    /* lire les metadonnées de la musique */

    QString title = info_tokens["Metadata/Title"];
    QString artist = info_tokens["Metadata/Artist"];
    QString relative_music_path = info_tokens["General/AudioFilename"];

    qDebug() << QString::asprintf("artist: '%s', title: '%s'", title.toStdString().c_str(), artist.toStdString().c_str());
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
