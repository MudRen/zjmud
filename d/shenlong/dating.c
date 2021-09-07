// dating.c 

#include <ansi.h>

inherit ROOM;

string* npcs = ({
	__DIR__"npc/boy",
	__DIR__"npc/boy2",
	__DIR__"npc/boy3",
	__DIR__"npc/boy4",
	__DIR__"npc/girl",
});

void create()
{
	set("short", "�����̴���");
	set("long", @LONG
����һ�����ȣ���ǰͻȻ�ֳ�һ������������˶�����������
ǧ��֮�ڡ�ֻ��һȺȺ������Ů�·���ɫ����վ�����λ���ࡢ�ס�
�ڡ�����ɫ�Ķ������꣬�����ȴ����Ů�����ϸ����̽���ÿһ��Լ
�а��ˣ�ɷ��׳�ۡ�
LONG );

	set("exits", ([
		"south" : __DIR__"damen",
		"north" : __DIR__"houting",
		"west"  : __DIR__"zhulin",
		"east"  : __DIR__"zoulang",
	]));
	set("valid_startroom","1");

	set("objects", ([
		npcs[random(sizeof(npcs))] : 1,
		npcs[random(sizeof(npcs))] : 1,
		__DIR__"npc/yunsumei": 1,
		CLASS_D("shenlong")+"/hong":  1,
		CLASS_D("shenlong")+"/wugen": 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (dir == "south")
		return 1;

	if (objectp(guarder = present("wugen daozhang", this_object())))
		return guarder->permit_pass(me, dir);

	return 1;
}
