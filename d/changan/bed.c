//Room: bed.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
һ�Ű�ɫ����齣�����ȥ��Ϊ���£�ɴ��ԧ��֮��ɢ����һ˿˿���㣮
LONG);
	set("exits", ([
		"out": __DIR__"kzsleep",
	]));
	set("no_fight", 1);
       	set("no_magic", 1);
	set("sleep_room",1);
	set("if_bed",1);

	setup();
}

