inherit  ROOM;

void  create  ()
{
	set("short",  "��ٵ�");
	set("long",  @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ���ۡ�����ͨ��
�ȹأ�������ֱ�ﳤ���ǡ�������һ��С·ͨ��ɽ�
LONG);
	set("exits",  ([
		"north"  :  "/d/village/hsroad1",
		"east"   :  __DIR__"hanguguan",
		"west"   :  __DIR__"zhongnan",
	]));

	set("outdoors", "changan");
	setup();
}

