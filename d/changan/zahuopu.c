//Room: zahuopu.c

inherit ROOM;

void create()
{
	set("short", "�ӻ���");
	set("long", @LONG
һ�����ֺŵ��ӻ��̡�����������Ӫ�������ڳ�������һ���Ѿ���
��һЩС�������������������ν��ף����Ǵ��װ��棬�ϰ����ճ�����
��Ҫ�Ķ���һ�������١��ټ�����������ƹ����������ӻ��̵�����
����һ���һ��á�
LONG);
	set("exits", ([
		"south" : __DIR__"huarui5",
	]));
	set("objects", ([
		__DIR__"npc/liu": 1,
	]));

	set("no_clean_up", 0);
	setup();
}

