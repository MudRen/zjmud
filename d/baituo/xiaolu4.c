//xiaolu4

inherit ROOM;

void create()
{
	set("short", "С·");
	set("long",
	     "������һ����ɽ��С·�����ֳ�һ�������������ɽ�������ѡ�\n"
	);
	set("outdoors", "baituo");
	set("exits", ([
		"north" : __DIR__"dongkou",
		"southwest" : __DIR__"xiaolu3",
	]));
	set("objects",([
		__DIR__"npc/shanzei2" : 1,
	]));

	setup();
}
