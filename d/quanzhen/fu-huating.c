// fu-huating ����
// By Lgg,1998.10

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������⻧�˼ҺȾ����µ����ڣ�һ��Сͤ�ӽ������������룬
����Χ����һЩ������(teng)��һ��΢�紵�����������ƺ�������
�Ļ���Ʈ������������
LONG
	);
	set("outdoors", "wugong");
	set("exits", ([
		"south" : __DIR__"fu-ceting",
		"west" : __DIR__"fu-xiaoyuan",
	]));
	set("item_desc", ([
	    "teng": "��Щ�ٺ��󳤵���Щ�����ˣ��ܲ�͸�磬����������¿϶��������ˡ�\n"
	]) );
	setup();
}
