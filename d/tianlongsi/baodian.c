inherit ROOM;

void create()
{
	set("short", "��ʥ����");
	set("long",@LONG
����һ�����Ĵ�������һ����Լ��ʮ��ߵķ��汦��ͨ���
��ҫ�ۡ������������ơ����������������̴ľ����������һ������Ի��
�������������ؿ�������Ī������Ī��һ�������顡
LONG );
	set("outdoors", "tianlongsi");
	set("exits", ([
		"north" : __DIR__"ta1",
	]));
	setup();
}
