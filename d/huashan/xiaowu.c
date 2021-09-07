// Room: /d/huashan/xiaowu.c

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�ּ�С��");
	set("long", @LONG
������ǻ�ɽ���ڵĵĸ���֮�ء���ʮ�����������ڵ�����н������
ֻ��Ϊ�˶�ػ�ɽ�������ţ�Ϊ�ˣ������˼���������
    ������輫Ϊ��ª��ֻ�����濪��һ��С�ţ��������һ��������
LONG );
	set("exits", ([ /* sizeof() == 4 */
	     "west": __DIR__"pingdi",
	     "east": __DIR__"neishi",
	]));
	set("objects", ([
	     CLASS_D("huashan") + "/feng-buping": 1,
	]));
	set("valid_startroom", 1);

	setup();
}

int valid_leave(object me, string dir)
{
	object guarder;

	if (! objectp(guarder = present("feng buping", this_object())))
		return 1;

	if (dir == "east")
		return guarder->permit_pass(me, dir);

	return 1;
}
