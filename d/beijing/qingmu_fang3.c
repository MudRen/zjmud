#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ľ��");
	set("long", @LONG
������һ�俴�ƺ���ͨ����ӣ�����ȴҪ��ͨ������Ӵ���������������
��һ�ų�������ػ����ľ�õ�Ⱥ��Χ��������������̸��
LONG );
	set("exits", ([
		"east" : __DIR__"qingmu_dayuan",
	]));

	set("objects", ([
		__DIR__"npc/qibiaoqing" : 1,
		__DIR__"npc/fangang" : 1,
		__DIR__"npc/fengjizhong" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

