// fu-houyuan.c ��Ժ
// By Lgg,1998.10

inherit ROOM;

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
�����Ǻ�Ժ���ߵ��������ζ����Ũ���ˡ�����ϸһ����
���ϱ���һ��Բ���ţ��ƺ������Ǵ����ﴫ�����ġ�����������
���ߣ����Ǻ�Ա��������ˡ�
LONG
	);
	set("outdoors", "wugong");
	set("exits", ([
		"southeast" : __DIR__"houhuayuan",
		"north" : __DIR__"fu-datang",
		"south" : __DIR__"fu-woshi",
	]));
	setup();
}