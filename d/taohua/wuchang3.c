// wuchang1.c

inherit ROOM;

void create()
{
	set("short", "���г�");
	set("long", @LONG
�������һ�����ָɽׯ���еĳ������󲿷ֵ��һ��������书����
һ���ĸ����Ժ����������ޣ������ϳ���ѧ��������������ͬ��
�ǣ��������ż����������ɵ����ˣ�����ȥ�ǳ��⺷��
LONG
	);
	set("exits", ([
		"north" : __DIR__"houyuan",
	]));

 	set("objects", ([
		"/clone/npc/tie-ren" : 3,
	]));

	set("outdoors", "taohua");
	set("for_family", "�һ���");
	setup();
}
