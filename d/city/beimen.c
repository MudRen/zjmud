// Room: /city/beimen.c
#include <room.h>

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���Ǳ����ţ���Ϊ����ʧ�𣬵����ڳ�ǽ���Ǻں����ģ���˰�ֽ
���ֵĹٸ���ʾ���Ե��ر����ۡ�������һƬ��ɽ���룬һ��
����С����ɽ�����Ѷ��ϡ�
LONG );
	set("item_desc", ([
		"����ʾ��" : (:look_gaoshi:),
	]));
	set("exits", ([
		"south" : __DIR__"beidajie2",
		"north" : "/d/shaolin/yidao",
		"west"  : "/d/huanghe/caodi1",
	    "east" : "/d/city/postofficer",
	]));
	set("objects", ([
		"/kungfu/class/yunlong/ma" : 1,
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 2,
	]));
	set("outdoors", "city");
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n��ҩ��\n";
}

