#include <QtCore>
#include <QtXml>
#include <QDebug>

//DOM method of reading xml

void ListElements(QDomElement root, QString tagname, QString attribute)
{
    QDomNodeList items = root.elementsByTagName(tagname);

     qDebug() << "Total items = " << items.count();

     for(int i = 0; i < items.count(); i++)
     {
        QDomNode itemnode = items.at(i);

        //convert to element
        if(itemnode.isElement())
        {
            QDomElement itemele = itemnode.toElement();
            qDebug() << itemele.attribute(attribute);
        }
     }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QDomDocument document;

    //Load the file
    QFile file("E:/test/MyXML.xml");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file";
        return -1;
    }
    else
    {
        if(!document.setContent(&file))
        {
            qDebug() << "Failed to load document";
            return -1;
        }
        file.close();
    }

    //get the root element
    QDomElement root = document.firstChildElement();

    //List the books
    ListElements(root,"Book", "Name");

    qDebug() << "\r\nMore Advanced\r\n";

    //Get the chapters
    QDomNodeList books = root.elementsByTagName("Book");
    for(int i = 0; i < books.count(); i++)
    {
        QDomNode booknode = books.at(i);
        //convert to an element
        if(booknode.isElement())
        {
            QDomElement book = booknode.toElement();
            qDebug() << "Chapters in " << book.attribute("Name");
            ListElements(book,"Chapter","Name");
        }
    }

    qDebug() << "Finished";

    return a.exec();
}
