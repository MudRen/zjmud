//Room: nanan-dadao.c

inherit ROOM;

void create ()
{
	set ("short", "�ϰ����");
	set ("long", @LONG
�����ǵ������ϰ������Ϊ���֣����˱��ǵľ����⣬���в�����
�����ÿͺ����ˡ��ϰ���������Ͼ��ǳ����ǵ��ϳ��ţ������ǹʻʹ�
�������֡�
LONG);
	set("exits", 
	([ //sizeof() == 2
		"south" : __DIR__"nanan-daokou",
		"north" : __DIR__"qinglong2",
		"east"  : __DIR__"gongbu",
	]));

	set("outdoors", "changan");
	setup();
}
