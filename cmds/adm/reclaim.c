// claim.c

inherit F_CLEAN_UP;

int filter(object ob);

int main(object me, string arg)
{
	object *ob;
	int i;
	int n;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	write(sprintf("һ������� %d ������.\n",
		      reclaim_objects()));
	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ: reclaim

�������еĶ��������Щ��Ӧ�����������ڴ��еı�����
TEXT );
	return 1;
}
