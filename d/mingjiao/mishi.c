// Room: /d/mingjiao/mishi.c
// Date: Java 97/04/9

#include <room.h>

#define BOOK	    "/clone/book/qiankun_book"

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
���ʯ�Ҽ��󣬶��ϴ������飬������Ȼ��ʯ�������˼�����ͻ
�����µ����������á����������·���δ�þ����ŵó���һ��һŮ��
�߽��������ã�ֻ����Ů������ץ��һ������������ذ�ף���������
���ؿڡ�
LONG );
	set("exits", ([
		"south" : __DIR__"midao9",
		"up"    : __DIR__"neishi",
	]));
	set("objects", ([
		__DIR__"obj/yangdt" : 1,
		__DIR__"obj/yangfr" : 1,
	]));
	set("xin_count", 1);
	create_door("south", "ʯ��", "north", DOOR_CLOSED);
	setup();
}

void init()
{
	add_action("do_ketou", "ketou");
}

int do_ketou()
{
	object me;
	object ob;

	me = this_player();
	message_vision("$N�ϵع����������������Ź�ǰ���������ؿ��˸�ͷ��\n", me);
	ob = find_object(BOOK);
	if (query("xin_count") < 1 || objectp(ob) && environment(ob))
	{
		tell_object(me, "���Ȼ�����Ź��ƺ������˷�Ū"
			    "����Ī�Ǳ���ȡ����ʲô������\n");
		return 1;
	}

	if (! objectp(ob)) ob = load_object(BOOK);
	set("xin_count", 0);
	new("/d/mingjiao/obj/yixin")->move(this_object());
	ob->move(this_object());
	tell_object(me, "ͻȻ��̧�ۿ����Ź����棬��һЩ��������"
		    "���˿���ԭ����һ���ź�һ����Ƥ��\n");
	return 1;
}
