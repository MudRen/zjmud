inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ��ͨ�����º�����ľ�����ȣ������ﾲ���ĵģ�ûʲô���߶���
��������������������
LONG );
	set("exits", ([
		"north" : __DIR__"was_zoulang2",
		"south" : __DIR__"was_dayuan",
		"east" : __DIR__"was_tinge",
		"west" : __DIR__"was_tingw",
	]));

	setup();
}

