// Room: /lingzhou/kongdi.c

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "���пյ�");
	set("long", @LONG
����ɽ���е�һ���յأ��������µķֲ�����ʮ��ľ�ݣ�������
����Ʈ�����Ͽգ�����С������׷�����֣�������û����ɵ�ſ����
����ɹ̫������Χɽ����ͬ���Ǿ�ľ���죬����ȥ�������һ��������
�͵�С�塣�����Ŀյ���������ľ�ݿ���ȥ�е�����עĿ�������Ͷ���
����һ��ɽ·��
LONG );
	set("exits", ([
		"east"     : __DIR__"dawu",
		"south" : __DIR__"tulu",
		"north" : __DIR__"qingxinquan", 
	]));
	set("objects", ([
		__DIR__"npc/nan" : 1,
		"/d/city/npc/wolfdog" : 2,
	]));
	set("outdoors", "lingzhou");
	setup();
}

