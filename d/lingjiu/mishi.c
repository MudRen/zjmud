
inherit ROOM;

void create()
{
    set("short", "����");
    set("long", @LONG
���Ǹ����������ң�ǽ�ϵ��͵Ʒ����谵�Ļƹ⡣
LONG );
    set("exits", ([
	"up" : __DIR__"huayuan",
    ]));
    set("objects",([
	"/clone/book/zhemei_book1" : 1,
	"/clone/book/zhemei_book2" : 1,
	"/clone/book/liuyang_book1" : 1,
	"/clone/book/liuyang_book2" : 1,
	"/clone/book/qijianpu" : 1,
    ]));
    setup();
}

