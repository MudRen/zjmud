//Room: dongan-dadao.c

inherit ROOM;

void create ()
{
	set ("short", "�������");
	set ("long", @LONG
�����ǵ����ֶ��������Ϊ���֣����˱��ǵľ����⣬���в�����
�����ÿͺ����ˡ�����������򶫾��ǳ����ǵ����µ��ڡ������ţ���
���ǹʻʹ��ķ�ڼ����
LONG);
	set("exits", 
	([ //sizeof() == 2
		"west" : __DIR__"fengxu3",
		"east" : __DIR__"dongan-daokou",
	]));

	set("outdoors", "changan");
	setup();
}
