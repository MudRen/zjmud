//Room: huarui4.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ�������һ��������Ĵ����Ҳ�ǳ����ǵľ�������һ��
��ʯ���̳ɵĽַ����ϱ߿ɼ�һЩ���סլ��������С��������ͷ�д�
������Ʈ��������ζ����Զ�������Ҽһ������׵����������д���
��ե���͵Ĵ���ζ��
LONG);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"minju4",
		"north" : __DIR__"xiaojinghu",
		"west" : __DIR__"nanan-daokou",
		"east" : __DIR__"huarui5",
	]));

	set("outdoors", "changan");
	setup();
}
