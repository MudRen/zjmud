// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�ഫ������ʼ����̩ɽ�����������������������͵���������
���±��꣬���û���š���ˣ����ͷ�����������Ϊ�����򡹡�
������֪����������һ��޴�ķ���ʯ���������������ˡ�������
���Բ��������������ڲ�Զ������һ������ƺ����˵������ʼ�ʵ�
����ʵ�λ�á�����������ɽ���߱�ᵽ��ʮ���̵���ڡ�
LONG );
	set("exits", ([
		"northup" : __DIR__"longmen",
		"southdown" : __DIR__"ertian",
	]));
	set("no_clean_up", 0);
	set("outdoors", "taishan");
	setup();
}

