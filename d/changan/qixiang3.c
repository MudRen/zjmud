////Room: qixiang3.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ����Ǳ�һ��������Ĵ����������ྻ������ʮ����
�֣���������������Ϣ����ֵ������̼��Ƽ������СС�ĵ��̱��ڶ�
�����ֵı�����һ�Ҷĳ����������������ϲ���ǡ��ĳ����ϰ�Ϊ�˷�
����ˣ�����������ֶ��濪��һ�ҵ��̡�
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"dangpu",
		"north" : __DIR__"duchang",
		"west" : __DIR__"qixiang2",
		"east" : __DIR__"beian-daokou",
	]));

	set("outdoors", "changan");
	setup();
}
