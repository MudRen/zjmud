inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����һ��ͨ�����´���ľ�����ȣ������ﾲ���ĵģ�ûʲô���߶���
ǰ��������µĴ���ˡ������ϵƻ�ͨ�����ǳ��Ŀ�������
LONG );
	set("exits", ([
		"north" : __DIR__"was_dadian",
		"south" : __DIR__"was_zoulang1",
	]));

	setup();
}

