//Room: xian-dadao.c

inherit ROOM;

void create ()
{
	set ("short", "�������");
	set ("long", @LONG
�����ǵ��������������Ϊ���֣����˱��ǵľ����⣬���в�����
�����ÿͺ����ˡ�����������������ǳ����ǵ���̩���ڡ������ţ���
���ǹʻʹ��ķ������
LONG);
	set("exits", 
	([ //sizeof() == 2
		"east" : __DIR__"fufeng3",
		"west" : __DIR__"xian-daokou",
	]));

	set("outdoors", "changan");
	setup();
}
