//Room: huarui6.c

inherit ROOM;

void create ()
{
	set ("short", "�����");
	set ("long", @LONG
������ǳ�������һ��������Ĵ����Ҳ�ǳ����ǵľ�������һ��
��ʯ���̳ɵĽַ����ϱ߿ɼ�һЩ���סլ����ͷ�д�������Ʈ�����
����ζ����Զ�������Ҽһ������׵����������д��˼�ե���͵Ĵ���
ζ��
LONG
	);
	set("exits", 
	([ //sizeof() == 4
		"south" : __DIR__"minju6",
		"north" : __DIR__"tuchangguan",
		"west" : __DIR__"huarui5",
		"east" : __DIR__"liande-nankou",
	]));

	set("outdoors", "changan");
	setup();
}
