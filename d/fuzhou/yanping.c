// Room: /d/fuzhou/yanping.c
inherit ROOM;

void create()
{
	set("short", "��ƽ��");
	set("long", @LONG
��ƽ�����з�����ռϪɽ֮�ۣ���ˮ½֮�ᣬ��Ϊ����֮��
������ɽ�Ʊ����������Ĺ��������ѹ���Ϊʡ�����ϣ��ʹط�
���ܲ��ᵡ��¡�������Թ���үʳ���˷����ͷ���ƽ������
LONG );
	set("exits", ([
		"northup"   : __DIR__"fzroad3",
		"southeast" : __DIR__"fzroad8",
		"southwest" : __DIR__"fzroad4",
	]));
	set("objects", ([
		"/d/city/npc/wujiang" : 1,
		"/d/city/npc/bing"    : 2,
	]));
	set("outdoors", "fuzhou");
	setup();
}

