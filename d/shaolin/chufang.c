// Room: /d/shaolin/chufang.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������ƣ��������ڣ���ζ�˱Ƕ�������ǽ��һ�����ɳ���
��̨��֧��ʮ���ڴ��������һ�ڷ����Ϸ������˴���������
���£��ֳ�ľ���ڽ��衣�����շ���ɮ���⣬��λ��ͷ��æ��
������н������¯�����ܡ�һλ����ɮ�������شߴ��š�
LONG );
	set("exits", ([
		"south" : __DIR__"fanting1",
	]));
	set("objects",([
		__DIR__"npc/shaofan-seng" : 2,
	]));
	set("resource/water", 1);
	setup();
}

