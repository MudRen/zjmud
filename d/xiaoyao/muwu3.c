// muwu3.c
inherit ROOM;
void create()
{
	set("short", "������");
	set("long", @LONG
����Ҳ��һ��ľ�ݣ������еİ���ʲô�򵥣�����ȴ�кܶ๤�ߣ�����
���������������������������ص�ľм��һ����֪����һ�������ļҡ�����
���ǵ��ɽ���æ���أ�������֪����������ʲô�أ�
LONG );
	set("exits", ([
		"north" : __DIR__"mubanlu",
	]));
	set("objects", ([
		CLASS_D("xiaoyao") + "/fengas": 1,
	]));
	setup();
}
