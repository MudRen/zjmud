// xiaolu11.c ��ɽС·
inherit ROOM;

void create()
{
	set("short", "��ɽС·");
	set("long", @LONG
�����Ǻ�ɽ�ϵ�С·������С·�������˹������޳����ģ�
Ҳ��ֻ����ǰ�Ĳ�ҩ�˲ȶ��ˣ��ֳ�����һ��С·�����ߵ����
�������·�ˡ�
LONG
	);
	set("outdoors", "quanzhen");
	set("exits", ([
		"east" : __FILE__,
		"west" : __DIR__"xiaolu10",
		"north" : __FILE__,
		"south" : __FILE__,
	]));
	set("no_clean_up", 0);

	setup();
}
