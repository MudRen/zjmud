// Room: /lingzhou/tulu.c

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "������·");
	set("long", @LONG
����ɽ�����·����ǿ����ͨ��һ���󳵣�·��������������ĳ�
��ӡ��·��ɽ����ȫ�ǲ����ľ������ȥ�ܲ�͸�磬������ľ�������
ż��������в��ܴ��Ƽž�����·�򶫱���������ת�˸��䣬��������
Լ���Կ�������һ����ݶ��ϵ����ġ�
LONG );
	set("exits", ([
		"south"     : __DIR__"luorilin2",
		"north" : __DIR__"kongdi", 
	]));
	set("no_clean_up", 0);
	set("outdoors", "lingzhou");
	setup();
}

