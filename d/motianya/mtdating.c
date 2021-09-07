//room: mtdating.c

inherit ROOM;

void create()
{
	set("short", "�¶�");
	set("long", @LONG
�����Ħ�����ˡ������ͺͺ�ģ���һ��С��Ҳû�У��嶥��Ҳ
ʮ�ֿ������������������ƣ������������ƶ�֮�У�ʹ���ľ�������
������һ��Сľ�ݡ�
LONG );
	set("outdoors", "xiakedao");
	set("exits",([
		"east" : __DIR__"mtxiaowu",
		"down" : __DIR__"mtyadi",
	]));
	set("objects",([
		__DIR__"npc/xieyan" : 1,
	]));

	set("outdoors", "motianya");
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;

	if (dir == "east" &&
	    objectp(ob = present("xie yanke", this_object())) &&
	    living(ob))
		return notify_fail("л�̿Ͱ���һ�����ȵ��������һ�������\n");

	return ::valid_leave(me, dir);
}
