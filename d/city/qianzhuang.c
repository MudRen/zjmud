// Room: /city/qianzhuang.c
inherit ROOM;
void create()
{
	set("short", "Ǯׯ");
	set("long", @LONG
����һ�����ֺŵ�Ǯׯ�����м��������ʷ����ȫ�����ض��зֵꡣ����
�е���Ʊ�����ǳ��ã�ͨ��ȫ����
    �ڶ����ǽ�Ϲ��˿�����(paizi)��
LONG );
	set("no_fight", 1);
	set("exits", ([
		"east" : __DIR__"beidajie1",
	]));
	set("item_desc", ([
		"�����ӡ�" : "��Ǯׯ�ṩ���·���\n"
		ZJOBACTS2+ZJMENUF(3,3,8,30)"��Ǯ:cun"ZJSEP"ȡǮ:qu"ZJSEP"����:check\n",
	]) );

	set("objects", ([
		__DIR__"npc/qian" : 1
	]));
	setup();
}

