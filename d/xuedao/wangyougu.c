// wangyougu.c
inherit ROOM;
void create()
{
	set("short", "���ǹ�");
	set("long", @LONG
�������Ǵ�������һ��Ƨ�����ڣ����¾����˼���ǰǰ���ᣬ���
СС���������������׵�ҫ�۵�ѩ�������š�����ɫ��ɽҰ��ѩ������
ҫ�ź�ɫ����ɫ�Ĺ��������ͷף��Թ�һ������¥�ɸ�������ǰ���֡�
����һ��С����֪ͨ���δ���
LONG );
	set("exits", ([
		"southwest"   : __DIR__"sroad8",
		"southeast" : __DIR__"sroad9",
		"north" : __DIR__"jingji/enter",
	]));
	set("objects", ([
		__DIR__"npc/zhuoma" :1,
		__DIR__"npc/yangzong" :1,
		CLASS_D("xuedao")+"/shanyong" : 1,
	]));
	set("outdoors", "xuedao");
	setup();
}

