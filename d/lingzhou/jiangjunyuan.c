// Room: /lingzhou/jiangjunyuan.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "��������Ժ");
	set("long", @LONG
�����ǽ������Ĵ�Ժ������һ�¿����İ����ձڣ����顰���ı�����
�ĸ����֣�����ǵ������Ļʵ���Ԫ껡�һɫ����ש�̵أ��м�������
����Ժ����ɨ����������լ�������Ǹ�СԺ��
LONG );
	set("exits", ([
		"east"  : __DIR__"xiaoyuan",
		"south" : __DIR__"neizai",
		"north" : __DIR__"jiangjungate",
	]));
	set("no_fight",1);
	set("objects", ([
		"/d/city/npc/jiading" : 2,
	]));
	setup();
	create_door("north" , "��ľ����", "south" , DOOR_CLOSED);
}
