// Room: /d/shaolin/houdian.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
����ģ�������߶���ˮĥʯ�ڣ��ο���ʮ���޺���Ф��
�����ˣ�������һ��ˮ����ˮ�澻���������������ᣬ��Ի����
��������������ˮ������������и��Ŷ���ͨ�����೤�������ȡ�
LONG );
	set("exits", ([
		"west" : __DIR__"zoulang2",
		"east" : __DIR__"zoulang3",
		"south" : __DIR__"guangchang4",
		"north" : __DIR__"wuchang",
	]));
	set("valid_startroom",1);
	set("resource/water",1);
	set("objects",([
		CLASS_D("shaolin") + "/hui-ru" : 1,
		CLASS_D("shaolin") + "/kong-jian" : 1,
		__DIR__"npc/seng-bing3" : 2,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	object kj;

	if (dir != "east" &&
	    dir != "west" &&
	    dir != "north" ||
	    ! objectp(kj = present("kong jian", this_object())))
		return ::valid_leave(me, dir);

	return kj->permit_pass(me, dir);
}
