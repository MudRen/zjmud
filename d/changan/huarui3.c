//Room: huarui3.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ�������һ��������Ĵ����Ҳ�ǳ����ǵľ�������һ��
��ʯ���̳ɵĽַ����ϱ߿ɼ�һЩ���סլ��������һ�һ��꣬��ͷ��
��������Ʈ��������ζ����Զ�������Ҽһ������׵����������д�
�˼�ե���͵Ĵ���ζ��
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"minju3",
		"north" : __DIR__"huadian",
		"west" : __DIR__"huarui2",
		"east" : __DIR__"nanan-daokou",
	]));

	set("outdoors", "changan");
	setup();
}
