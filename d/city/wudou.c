#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�䶷��");
	set("long", "���ֺ��ܻ�ս�д�ĵط�������û�й���û�������ͷ�������Ծ��鷢�ӣ�" );
	set("exits", ([
		"south":__DIR__"ximenroad",
	]));
	set("no_fight",1);
	set("action_list", ([
		"������̨":"wudou",
	]));
	set("objects", ([
	]));
	setup();
}

void init()
{
	add_action("wudou","wudou");
}

int wudou()
{
	object me = this_player();

	me->set_temp("backup/killer", me->query_killer());
	me->set_temp("backup/want", me->query_want());
	me->set_temp("in_pkd", 1);
	me->set("backup/condition", me->query_condition());
	me->clear_condition();
	me->move("/d/city/leitai2");
	return 1;
}
