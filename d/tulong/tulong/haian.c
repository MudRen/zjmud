#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "ε������");
	set("long", @LONG
�ޱ��޼ʵĴ󺣾�����ǰ�ˡ�������棬һϴ�����ÿ͵�һ·�Ͷ١�����
���������е���ζ������΢΢���Ų��ˡ������ĵĺ�ˮ����ӿ���Ľ�׵��˻���
����Ʈ������ı���ãã�Ĵ���û��һ�㷫Ӱ����ĿԶ�������콻�紦��
��һƬ���ֲ��������Ǻ����������졣
LONG );

	set("exits", ([
		"south" : "/d/beijing/haigang",
		"east" :  __DIR__"shatan",
	]));

	set("objects", ([
		"/d/tulong/yitian/npc/huiyue" : 1,
		"/d/tulong/yitian/npc/miaofeng" : 1,
	]));

	set("no_clean_up", 0);
	set("outdoors", "tulong");
	setup();
}

