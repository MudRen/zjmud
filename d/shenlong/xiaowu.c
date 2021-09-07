#include <ansi.h>

inherit ROOM;
string* books = ({
	"/clone/book/book-bamboo",
	"/clone/book/book-paper",
	"/clone/book/book-stone",
	"/clone/book/book-iron",
});


void create()
{
    set("short", "С��");
    set("long", @LONG
һ��С�ݣ�ֻ��ǽ�Ϲ���������������ֻ��������Ҳ������ƽ
ʱ�ѵ�һ���ĸ��ָ������鼮��һ����òӢ���������ʿ������һ��
�ֻ�����̾����
LONG
    );

    set("exits", ([
	"south" : __DIR__"caodi",

    ]));
    set("objects", ([
		CLASS_D("shenlong")+"/lu": 1,
		books[random(sizeof(books))] : 1,
		books[random(sizeof(books))] : 1,
    ]));
    set("outdoors", "shenlong");
    setup();
}


