#include "GameItems/note.h"
#include "songfile.h"

#include <QDebug>

#include <QTextStream>
#include <QFile>
#include <QRegExp>

static NoteType columnToType[] = {
    NoteType::NORMAL,
    NoteType::BONUS,
    NoteType::TRAP,
    NoteType::NORMAL,
    NoteType::BONUS,
    NoteType::TRAP,
    NoteType::SMASH
};

static void tokenize(QTextStream&, QMap<QString,QString>&, QList<QString>&);

void tokenize(QTextStream& instream, QMap<QString,QString>& info_tokens, QList<QString>& notes_tokens)
{
    /* Regexes for the different contents */
    QRegExp sectionrx("\\[([^]]+)\\]");
    QRegExp propertyrx("([^:\\d]+):[\\s]?(.+)");
    QRegExp hitobjectrx("(\\d+,\\d+,\\d+),.+");

    QString section = "Invalid";
    QString line;

    while(instream.readLineInto(&line)) {
        if (sectionrx.indexIn(line) > -1)
            section = sectionrx.capturedTexts()[1];
        if (propertyrx.indexIn(line) > -1)
            info_tokens.insert(section + "/" + propertyrx.capturedTexts()[1], propertyrx.capturedTexts()[2]);
        if (hitobjectrx.indexIn(line) > -1)
            notes_tokens.append(hitobjectrx.capturedTexts()[1]);
    }
}

bool loadFromFile(QString& path, QList<Note *> *upNotes, QList<Note *> *downNotes)
{
    /* Open the file */
    QFile infile(path);
    if (!infile.open(QFile::ReadOnly | QFile::Text))
        return false;
    QTextStream in(&infile);

    QMap<QString,QString> info_tokens;
    QList<QString> notes_tokens;
    tokenize(in, info_tokens, notes_tokens);

    /* lire les metadonnées de la musique */

    QString title = info_tokens["Metadata/Title"];
    QString artist = info_tokens["Metadata/Artist"];

    qDebug() << title << artist;

    /* lire les notes dans les listes */

    for (QString note : notes_tokens) {
        QStringList settings_list = note.split(',');
        int x         = settings_list.takeFirst().toInt();
        int y         = settings_list.takeFirst().toInt();  // not important
        int timestamp = settings_list.takeFirst().toInt();
        Q_UNUSED(y);

        int column = (x * 7) / 512;
        NoteType type = columnToType[column];

        Note *new_note = new Note(type, timestamp);

        if (column > 2)
            upNotes->append(new_note);
        else
            downNotes->append(new_note);
    }

    infile.close();
    return true;
}
