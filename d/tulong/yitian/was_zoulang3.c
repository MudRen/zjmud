inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ��ͨ�����º���ľ�����ȣ������ﾲ���ĵģ�ûʲô���߶���
�������µĴ���ˡ�
LONG );
	set("exits", ([
		"north" : __DIR__"was_houdian",
		"south" : __DIR__"was_dadian",
	]));

	setup();
}

