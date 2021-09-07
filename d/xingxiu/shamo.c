// Room: /d/xingxiu/shamo4.c

#include <room.h>
inherit ROOM;

void create()
{
       set("short","��ɳĮ");
       set("long", @LONG
����һƬһ���޼ʵĴ�ɳĮ����һ��������ʧ�˷���
����Ҫ�߳����ɳĮ�������¡�
LONG );

	set("exits", ([
		"east" : __FILE__,
		"west" : __FILE__,
		"south" : __FILE__,
		"north" : __FILE__,
	]));

	set("outdoors", "xiyu");
	set("no_map", "����ĵ��������������޴����ֻ��Ƶ�ͼ��\n");

	setup();
}

int valid_leave(object me, string dir)
{
	int water, food;
	int qi, jing;
	string dest;

	if (interactive(me))
	{
		water = me->query("water");
		food = me->query("food");
		water -= (random(2) + 1) * water / 40 + 5;
		food -= (random(2) + 1) * food / 40 + 5;
		if (water < 0) water = 0;
		if (food < 0) food = 0;
		me->set("water", water);
		me->set("food", food);

		qi = me->query("max_qi") * 5 / 100 + random(10);
		jing = me->query("max_jing") * 5 / 100 + random(10);

		if (me->query("qi") < qi || me->query("jing") < jing)
		{
		  	write("���Ѿ��е������ˣ�ڤڤ����������˰���̧����ɽ���¡�\n");
		  	me->move(__DIR__"shanjiao");
		  	me->unconcious();
			return -1;
		}

		me->receive_damage("qi", qi);
		me->receive_damage("jing", jing);
	}

	dest = sprintf("/d/xingxiu/shamo%d", random(10) + 1);
	me->move(dest);

	if (interactive(me))
	{
		switch (random(3))
		{
		case 0:
			write("�㶥�ŷ�ɳ�߰��ߣ�����û���߳�ɳĮ��\n");
			break;
	
		case 1:
			write("�����������Ұ�Ļ�ɳ��̾�˿������޾���ɵ����š�\n");
			break;
	
		case 2:
			write("��һ��������ǰŲ�ţ����ѷֲ�������\n");
			break;
		}
	}
	return -1;
}
