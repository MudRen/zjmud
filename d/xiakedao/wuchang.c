// ROOM: /xiakedao/wuchang.c

inherit ROOM;
void create()
{
	set("short", "�䳡");
	set("long", @LONG
����һ������ʯ���������װ�¼����ˣ����Է���ʮ�˰����
��������ɢ�ķ���������ӣ��м�һ��������ɺ�ɫ�ĵ�̺����ʿ��
������������书��
LONG );
	set("exits", ([
		"west" : __DIR__"shibi",
	]));
	setup();
}
