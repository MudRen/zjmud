// Room: /d/xiakedao/road7.c
  
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "�б�ʯ");
	set("long", @LONG
������Ǽб�ʯ���˴�ɽ�ƶ��ͣ����˵����޲��ľ�����������
����˵����ֻ��ƽ����ȥ����ɽ����һ����С�ģ������ױ����鵽
�¹�֮�С�
LONG );
	set("outdoors", "xiakedao");
	set("exits", ([
		"southup"   : __DIR__"road8",
		"northdown" : __DIR__"road6",
	]));
	set("outdoors", "xiakedao");
	setup();
}
