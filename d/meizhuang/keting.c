// keting.c
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "ӭ��ͤ"); 
	set("long", @LONG
ͨ��������磬��������÷ׯ��ӭ��ͤ��������Ȼֻ��һ��ʯ��
(table) �ͼ���ʯ�ʣ���ȴ��һ����Ⱦ��ʯ�ʺ�ʯ��֮��Ŀ�϶�ܴ�
���Ƿ��������������໥���ѡ�
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
	    "south" : __DIR__"dating",
	    "north" : __DIR__"senlin1",
	]));

	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/shi.c" : 1,
	]));
	set("no_clean_up", 0);
	set("item_desc", ([
		"table": "һ�ź�ƽ����ʯ�������ǿ���ȥ�ܾ�����Щ�Ź֣�Ҫ��û��"
			 "���ڣ�����������ȥ�鿴һ����\n"
	]));

	setup();
}
void init()
{
	add_action("do_zuan", "zuan");
}

int do_zuan(string arg)
{
	object ob;
	string dir;
	object me = this_player();

	if (arg != "table")
	{
		write("��Ҫ���Ķ��ꣿ\n");
		return 1;
	}

	if (objectp(ob = present("shi lingwei", this_object())) &&
	    living(ob))
	{
		write("��͵͵�Ŀ��˿�" + ob->name() + "������������\n");
		return 1;
	}

	write("��������ŵ��Ƶ�ʯ���ĺ��棬����������һ��С����\n");
	if((int)me->query_skill("dodge",1) >= 30)
	{
	      write("��Ѿ���ţ����֮���������Լ�����һ�������صĵص��\n");
	      me->move(__DIR__"didao1");
	      return 1;
	}
	write("����������һ�º����һ��С���������겻��ȥ��\n");
	me->add("jing", -10);
	me->add("qi", -10);

	return 1;
}
