#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "ͥԺ");
	set("long", @LONG
���������µĴ�Ժ����ɨ�÷ǳ��ɾ�����Ժ�����Ǽ�����ݣ�ȫ����
ľ��ɣ������ľ����ľ�Ͼ���ȥƤ����Ȼ���ӣ�ȴ���Ժ���Ե�һ�����
�Ի͵ĵ��ý�Ȼ��ͬ��
LONG );
	set("exits", ([
		"out" : __DIR__"was_damen",
		"east" : __DIR__"was_change",
		"west" : __DIR__"was_changw",
		"north" : __DIR__"was_zoulang1",
	]));

	set("objects", ([
		__DIR__"npc/zhao1" : 1,
		__DIR__"npc/qian2" : 1,
		__DIR__"npc/sun3" : 1,
		__DIR__"npc/li4" : 1,
		__DIR__"npc/zhou5" : 1,
		__DIR__"npc/wu6" : 1,
		__DIR__"npc/zheng7" : 1,
		__DIR__"npc/wang8" : 1,
	]));

	setup();
}

int valid_leave(object me,string dir)
{
	object ob;

	if ( dir == "north" && ob = present("zhao yishang", this_object()))
	{
		message_vision(CYN "$N�ȵ���������Ҳ���Ҵ���ȥ���ɣ�"NOR"\n",ob,me);
		ob->kill_ob(me);
		ob = present("qian erbai", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob = present("sun sanhui", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob = present("li sicui", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob = present("zhou wushu", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob = present("wu liupo", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob = present("zheng qimie", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		ob = present("wang bashuai", this_object());
		if (objectp(ob)) ob->kill_ob(me);
		return notify_fail("�򱱵�·�����������ס�ˡ�\n");
	}
	return 1;
}

