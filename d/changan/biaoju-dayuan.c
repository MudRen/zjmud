//Room: biaoju-dayuan.c

inherit ROOM;

void create()
{
	set("short", "�����ھִ�Ժ");
	set("long", @LONG
Ժ������ѷ���ʮ�����ò�ϯ���ŵĿ��ڳ�����ϯ�ϻ�����ѩ����
��������£�б����һ�潴ɫ���ߵ����죬���紵���������죬ʹ��
�����ֱ治���ý�����������������ϻ�������ʨ�ӡ���Ժ�ﲻʱ��ʦ
������
LONG);
	set("exits", ([
		"north" : __DIR__"biaoju-damen",
		"south" : __DIR__"biaoju-dating",
	]));
	set("objects", ([
		__DIR__"npc/biaotou" : 1,
		__DIR__"npc/tang" : 2,
	]) );
    
	set("outdoors", "changan");
	setup();
}
