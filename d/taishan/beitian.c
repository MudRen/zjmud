// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����λ��ʯ��ɽ�ı�´����᷶��ı�����ڣ�·����һʯ����
����д�š����䡹���֡�
LONG );
	set("exits", ([
		"southdown" : __DIR__"zhangren",
	]));
	set("no_clean_up", 0);
	set("outdoors", "taishan");
	setup();
}

