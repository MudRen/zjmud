// Room: /d/gaibang/undersl.c
// Date: Haa 96/03/22

#include <room.h>

inherit ROOM;

void create()
{
	set("short", "�ݽǱ�");
	set("long", @LONG
�������Ǽҳ�����ľ������档�����������õģ������˸�����
�����ؤ������ռ�����ͭ�����ȡ�������ͨ��ؤ�������ͨ����
���ﻹ���ż���ľ�ˣ��Ѿ���Ϊ�¾ɣ����������Ǵ�����������͵��
���ģ����϶��ż������Ⱥ�ţƤ�ƴ���Ҳ��֪����˭��������ġ�
LONG );
	set("exits", ([
		"up"	: "/d/shaolin/chufang2",
		"southwest" : __DIR__"slandao2",
	]));
	set("objects",([
		CLASS_D("gaibang") + "/he-bj" : 1,
		"/clone/npc/mu-ren" : 4,
		"/d/city/obj/jitui" : 3,
		"/d/city/obj/jiudai" : 2,
	]));
	set("for_family", "ؤ��");
	setup();
}
