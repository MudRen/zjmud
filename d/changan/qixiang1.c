//Room: qixiang1.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ����Ǳ�һ��������Ĵ����������ྻ������ʮ����
�֣���������������Ϣ����ֵ������̼��Ƽ������СС�ĵ��̱��ڶ�
�����ֵı�����һ����¥��������һ�ҿ�ջ��
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"kezhan",
		"north" : __DIR__"jiulou",
		"west" : __DIR__"yongtai-beikou",
		"east" : __DIR__"qixiang2",
	]));

	set("outdoors", "changan");
	setup();
}
