// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "��ڷ�");
	set("long", @LONG
λ��̩���س��Ա�Լһ��˴��ǵ�̩ɽ����ڡ��ഫ�����
ϼԪ����������ϷŪ������Ͷ���廨Ь�Զ�̩ɽ�ؽ磬�����ϼԪ
��ֻ�ܰ��廨Ь��ɽ�������˴����Ӵ�̩ɽ���Դ�Ϊ��㡣
LONG );
	set("exits", ([
		"northup" : __DIR__"baihe",
		"south"   : __DIR__"taishanjiao",
		"west"    : "/d/huanghe/huanghe5",
	]));

	set("objects", ([
		CLASS_D("misc") + "/shanzheng" : 1,
	]));

	set("outdoors", "taishan");
	setup();
}

