int is_jjroom() { return 1; }

int valid_leave(object me, string dir)
{
	if(random(2))
	{
		tell_object(me,"��æ�У���һ��С�ĵ���һ�ӣ�\n");
		me->start_busy(2);
		return 1;
	}
	return ::valid_leave(me, dir);
}
