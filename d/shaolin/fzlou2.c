inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����ҳ����࣬����һ����һ���ţ�һ����������ǽ��д
�Ŵ���һ���������֡�һλ��ü��Ŀ�Ļ�����ɮ������������
�ϴ�����
LONG );
	set("exits", ([
		"south" : __DIR__"fzlou1",
	]));
	set("objects",([
		CLASS_D("shaolin") + "/xuan-ci" : 1,
	]));
	setup();
}
