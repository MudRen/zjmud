// Room: /lingzhou/gonggate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "�ʹ��㳡");
	set("long", @LONG
����������Ļʹ��㳡��������һ�ȿ����������ţ��������ȭͷ���
ͭ�����ŵ�����վ�������¼���������ʿ���䱸���ϡ�
LONG );
	set("exits", ([
		"south"  : __DIR__"gonggate",
		"east"  : __DIR__"biangate",
		//"west"  : "/d/fuben/xixia/jiaochang",
	]));
	set("no_fight",1);
	set("objects", ([
		__DIR__"npc/gongweishi" : 2,
	]));
	create_door("south" , "���Ṭ��", "north" , DOOR_CLOSED);
	setup();

}


