// room: /d/xingxiu/tianroad5.c
inherit ROOM;

void create()
{
	set("short", "��ɽɽ·");
	set("long", @LONG
��������ɽ��´��ɽ���ɽ�ϴ����������ɪɪ������·����һƬ��Ҷ�֡�
������ȥ������ңң�ɼ����ϱ��и��������ɽ��(cave)��
LONG );
	set("exits", ([
	    "westup" : __DIR__"tianroad6",
	    "eastdown" : __DIR__"tianroad4",
	    "enter" : __DIR__"cave",
	]));
	set("objects", ([
	       __DIR__"npc/caiyaoren" : 1, 
	]));
	set("item_desc", ([
	      "��ɽ����" : "�������ɽ����Ʈ��һ�����磬�ŵ���ֱ����¡�\n"
	]) );
	set("outdoors", "xingxiu");
	setup();
}

