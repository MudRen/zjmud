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
		"north" : __DIR__"qingmu_dayuan",
	]));
	set("objects", ([
		 __DIR__"npc/guananji" : 1,
		 __DIR__"npc/qianlaoben" : 1,
		 __DIR__"npc/jialaoliu" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

